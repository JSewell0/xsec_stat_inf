from iminuit import Minuit
from iminuit.cost import poisson_chi2, Template, template_chi2_da
import numpy as np
from scipy.stats import norm, truncexpon
from scipy.optimize import root_scalar, minimize
import matplotlib.pyplot as plt
from IPython.display import display
from collections import defaultdict
from joblib import Parallel, delayed
import ROOT as rt
import pandas as pd
import csv


def generate(rng):

    b1 = np.array([34.9,16.2,5.2,3.1,2.9,1.29,1.19,1.02])
    b2 = np.array([749.4,332.4,176.4,99.4,60.7,34.7,26.9,18.8,3.5])
    b3 = np.array([1244,555,311,156,93,77.1,55.8,30.2,7.5])
    b4 = np.array([88.1,48.2,25.4,15.5,12.3,7.9,9.6,6.2,0.9])

    bN = np.concatenate((b1,b2,b3,b4))
    xe = np.linspace(1,35,36)

    n = rng.poisson(bN)
    return xe, n, bN

def write_csv(outfile_name,data_arr):
    
    fields = ['mass']
    masses = []
    models = []
    rows = []
    
    for data in data_arr:
        if str(data[1]) not in fields:
            fields.append(str(data[1]))
            models.append(data[1])                    
        if data[0] not in masses:
            masses.append(data[0])
        
    for mass in masses:
        temp = [mass]
        for model in models:
            for data in data_arr:
                if mass == data[0] and model == data[1]:
                    temp.append(data[3]/data[2])
        rows.append(temp)

    with open(outfile_name,"w") as f:

        csvwriter = csv.writer(f)
        csvwriter.writerow(fields)
        csvwriter.writerows(rows)
        print(f"Wrote {outfile_name}!")

def get_masses(file_name,index):

    arr = []
    data_table = pd.read_csv(file_name)
    masses = data_table.iloc[:,index]
    for mass in masses:
        arr.append(int(f"{mass:.0f}"))
    return arr

def get_template(file_name,model,sr,nlsp_mass):

    template = np.array([])
    for i, partial in enumerate(model):
        hist_name = f"TChi{partial}_{sr}_{nlsp_mass}_100"
        tf = rt.TFile(file_name,"r")
        h1 = tf.Get(hist_name)
    
        t = np.array([])
        for j in range(1,h1.GetNbinsX()+1):
            t=np.append(t,h1.GetBinContent(j))

        template = np.append(template,t) if i == 0 else np.add(template,t)
            
    return template

def find_cl(outfile_name,file_name,model,nlsp_mass,debug=False):
    signal_template = np.concatenate((get_template(file_name,model,"WHSR",nlsp_mass),get_template(file_name,model,"WSR",nlsp_mass),get_template(file_name,model,"HSR",nlsp_mass),get_template(file_name,model,"bVeto",nlsp_mass)))
    avg = np.array([])
    if debug:
       plt.stairs(signal_template,np.linspace(1,35,36),fill=True, color="darkorange", alpha=0.5,label="Signal Template")
       plt.show()
       return 0
    else:
        for i in range(10):
            MuS = np.array([])
            MuB = np.array([])
            for x in range(1000):
                rng = np.random.default_rng()

                xe, n, bkg_template = generate(rng)

                templates = np.array([bkg_template,signal_template])
                truth = bkg_template.sum(), signal_template.sum()

                c = Template(n, xe, templates, method="da") # Dembinski, Abdelmotteleb
                m = Minuit(c, *truth)
                m.fixed["x0"]=True
                m.migrad()
                m.hesse()
                # r = m.fmin.reduced_chi2
                MuB = np.append(MuB,m.values[0])
                MuS = np.append(MuS,m.values[1])

            avg = np.append(avg,np.sort(MuS)[950])

            with open(outfile_name,"a") as f:
                f.write(f"mass: {nlsp_mass} | num of signal events: {sum(signal_template):.3f} | \u03bc cl = {np.mean(avg):.3f} +- {np.std(avg):.3f}\n")
            return [nlsp_mass,model,sum(signal_template),np.mean(avg)]







def main():     
    '''
    Need to change settings when working with different scenarios e.g. 1b,1a,2b etc.
    '''
    ###SETTINGS###

    models = [["HZ+","WH+","WW"],["HZ-","WH-","WW"]]
    masses = get_masses("rates1b.csv",17) #number is index of collum w/ mass data
    csv_arr = []

    file_name = "1b_signal_templates.root"
    outfile_name = "1b_cl_yields.txt"
    outcsv_name = "1b_rvals.csv"

    ###END OF SETTINGS###

    open(outfile_name,"w").close()
    for model in models:
        print(f"========== model: {model} ==========")
        with open(outfile_name,"a") as f:
            f.write(f"======================= model: {model} =======================\n\n")

        for mass in masses:
            print(f"mass: {mass}")
            csv_arr.append(find_cl(outfile_name,file_name,model,mass))

    print(f"\nWrote {outfile_name}!\n")
    write_csv(outcsv_name,csv_arr)

if __name__ == "__main__":
    main()
