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

def clean_data(data):
    temp = np.array([])
    for entry in data:
        if entry >= 0:
            temp = np.append(temp,entry)
        else:
            temp = np.append(temp,0)
    return temp

def generate(rng):

    b1 = np.array([34.9,16.2,5.2,3.1,2.9,1.29,1.19,1.02])
    b2 = np.array([749.4,332.4,176.4,99.4,60.7,34.7,26.9,18.8,3.5])
    b3 = np.array([1244,555,311,156,93,77.1,55.8,30.2,7.5])
    # b4 = np.array([88.1,48.2,25.4,15.5,12.3,7.9,9.6,6.2,0.9])
    error = np.array([5.4,3.3,1.3,1.3,1.2,0.62,1.1,1.1,46.1,32.5,13.5,9.9,6.9,4.7,3.6,3.2,1.7,61,27,20,14,10,8,7.1,4.8,2.5,9.2,6.7,4.4,3.7,3.1,2.1,2.8,2.2,0.7])
    
    bkg_template = np.concatenate((b1,b2,b3))
    bin_locs = np.linspace(1,len(bkg_template),len(bkg_template)+1)
    
    # bkg_data = rng.normal(bkg_template,error)
    # print(len(bkg_template))
    # print(f"bkg temp \n{bkg_template}\n")
    # print(len(bkg_data))
    # print(f"bkg data \n{bkg_data}\n")
    
    data = rng.poisson(bkg_template)#clean_data(bkg_data))
    return bin_locs, data, bkg_template

def write_csv(outfile_name,data_arr):
    
    fields = ["mass"]
    masses = []
    models = []
    rows = []
    
    for data in data_arr:
        if str(data[1]) not in fields:
            fields.append(str(data[1]))
            models.append(data[1])                    
        if str(data[0]) not in masses:
            masses.append(str(data[0]))
        
    for mass in masses:
        temp = [mass]
        for model in models:
            for data in data_arr:
                if mass == str(data[0]) and model == data[1]:
                    temp.append(str(data[3]/data[2]))
        rows.append(temp)

    with open(outfile_name,"w") as f:
        csvwriter = csv.writer(f)
        csvwriter.writerow(fields)
        csvwriter.writerows(rows)
        print(f"Wrote {outfile_name}!\n")

def get_masses(file_name,index):

    arr = []
    data_table = pd.read_csv(file_name)
    masses = data_table.iloc[:,index]
    for mass in masses:
        arr.append(int(f"{mass:.0f}"))
    return arr

def get_template(file_name,model,sr,nlsp_mass):

    template = np.array([])
    

    hist_name = f"TChi{model}_{sr}_{nlsp_mass}_100"
    tf = rt.TFile(file_name,"r")
    h1 = tf.Get(hist_name)
    t = np.array([])

    for j in range(1,h1.GetNbinsX()+1):
        t=np.append(t,h1.GetBinContent(j))

    template = np.append(template,t)
            
    return template

def find_cl(outfile_name,file_name,model,nlsp_mass,debug=False):

    signal_template = np.concatenate((get_template(file_name,model,"WHSR",nlsp_mass),get_template(file_name,model,"WSR",nlsp_mass),get_template(file_name,model,"HSR",nlsp_mass)))
    avg = np.array([])
    
    if debug:
       plt.stairs(signal_template,np.linspace(1,35,36),fill=True, color="darkorange", alpha=0.5,label="Signal Template")
       plt.show()
       return 0
    else:
        for i in range(5):
            signal_yields = np.array([]) # array of signal yields found by iminuit
            for x in range(1000):
                rng = np.random.default_rng()

                bin_locs, data, bkg_template = generate(rng)

                templates = np.array([bkg_template, signal_template])
                truth = [bkg_template.sum(), signal_template.sum()]

                cost_fn = Template(data, bin_locs, templates, method="da") # Dembinski, Abdelmotteleb
                m = Minuit(cost_fn, *truth)
                m.fixed["x0"]=True
                m.migrad()
                m.hesse()
                # r = m.fmin.reduced_chi2
                signal_yields = np.append(signal_yields,m.values[1])

            avg = np.append(avg,np.sort(signal_yields)[950])

        with open(outfile_name,"a") as f:
            f.write(f"mass: {nlsp_mass} | num of signal events: {sum(signal_template):.3f} | \u03bc cl = {np.mean(avg):.3f} +- {np.std(avg):.3f}\n")
        return [nlsp_mass,model,sum(signal_template),np.mean(avg)]

def main():     

    model = "WH"
    masses = [250,300,350,400,450,500,550,600,650,700,725,775,800,850,900,950,1000]#get_masses(f"1b_rvals.csv",0) #number is index of collum w/ mass data 

    file_name = "sms_signal_templates.root"
    outfile_name = f"{model}sms_cl_yields.txt"
    outcsv_name = f"{model}sms_rvals_avg.csv"

    csv_arr = []
    open(outfile_name,"w").close()

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
