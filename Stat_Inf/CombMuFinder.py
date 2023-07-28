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
<<<<<<< HEAD
import pandas as pd


def generate(error,rng):

    b1 = np.array([34.9,16.2,5.2,3.1,2.9,1.29,1.19,1.02])
    b2 = np.array([749.4,332.4,176.4,99.4,60.7,34.7,26.9,18.8,3.5])
    b3 = np.array([1244,555,311,156,93,77.1,55.8,30.2,7.5])
    b4 = np.array([88.1,48.2,25.4,15.5,12.3,7.9,9.6,6.2,0.9])

    bN = np.add(np.concatenate((b1,b2,b3,b4)),error)
    xe = np.linspace(1,35,36)

    n = rng.poisson(bN)
    return xe, n, bN
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

def find_cl(outfile_name,file_name,model,nlsp_mass,error,debug=False):
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

               xe, n, bkg_template = generate(error,rng)

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
  



perror = np.array([5.4,3.3,1.3,1.3,1.2,0.62,1.1,1.1,46.1,32.5,13.5,9.9,6.9,4.7,3.6,3.2,1.7,61,27,20,14,10,8,7.1,4.8,2.5,9.2,6.7,4.4,3.7,3.1,2.1,2.8,2.2,0.7])
merror = np.negative(np.array([5.4,3.3,1.3,1.3,1.2,0.62,.5,0.43,46.1,32.5,13.5,9.9,6.9,4.7,3.6,3.2,1,61,27,20,14,10,8,7.1,4.8,2.5,9.2,6.7,4.4,3.7,3.1,2.1,2.8,2.2,0.7]))
zerror = np.zeros(len(perror))

models = [["WZ+","WH+","WW"],["WZ-","WH-","WW"]]
masses = get_masses("1arates.csv",9)

file_name = "1a_signal_templates.root"
outfile_name = "1a_cl_yields.txt"

open(outfile_name,"w").close()

for model in models:
    print(f"========== model: {model} ==========")
    with open(outfile_name,"a") as f:
        f.write(f"======================= model: {model} =======================\n\n")
        
    for mass in masses:
        print(f"mass: {mass}")
        find_cl(outfile_name,file_name,model,mass,zerror)
=======

def generate(error,rng):
    
    # bN = np.array([])
    # xe = np.array([])
    
    # if sr == "WH":
    b1 = np.array([34.9,16.2,5.2,3.1,2.9,1.29,1.19,1.02])
    #     xe = np.array([200,250,300,350,400,450,500,600,1000])
    # elif sr == "W":
    b2 = np.array([749.4,332.4,176.4,99.4,60.7,34.7,26.9,18.8,3.5])
    #     xe = np.array([200,250,300,350,400,450,500,600,800,1000])    
    # elif sr == "H":
    b3 = np.array([1244,555,311,156,93,77.1,55.8,30.2,7.5])
    #     xe = np.array([200,250,300,350,400,450,500,600,800,1000])

    bN = np.concatenate((b1,b2,b3))
    xe = np.linspace(1,26,27)

    n = rng.poisson(bN+error)
    return xe, n, bN

def get_template(hist_name,scale=1):

    file_name = "signal_templates.root"
    tf = rt.TFile(file_name,"r")
    h1 = tf.Get(hist_name)
    
    t = np.array([])
    for i in range(1,h1.GetNbinsX()+1):
        t=np.append(t,h1.GetBinContent(i))
    t=t*scale
    return t


MuS = np.array([])
MuB = np.array([])
RChi2 = np.array([])

sr1 = "WH"
sr2 = "W"
sr3 = "H"
num_runs = 1000

hist_name1 = "TChiWH_"+sr1+"SR_1000_100"
hist_name2 = "TChiWH_"+sr2+"SR_1000_100"
hist_name3 = "TChiWH_"+sr3+"SR_1000_100"
error = np.array([5.4,3.3,1.3,1.3,1.2,0.62,1.1,1.1,46.1,32.5,13.5,9.9,6.9,4.7,3.6,3.2,1.7,61,27,20,14,10,8,7.1,4.8,2.5])
errorM = np.array([5.4,3.3,1.3,1.3,1.2,0.62,.5,0.43,46.1,32.5,13.5,9.9,6.9,4.7,3.6,3.2,1,61,27,20,14,10,8,7.1,4.8,2.5])
sT = np.concatenate((get_template(hist_name1),get_template(hist_name2),get_template(hist_name3)))
avg = np.array([])

for i in range(1):
    MuS = np.array([])
    MuB = np.array([])
    for x in range(num_runs):
        rng = np.random.default_rng()
        xe, n, bT = generate(error,rng)
        templates = np.array([bT,sT])
        truth = bT.sum(), sT.sum()

        c = Template(n, xe, templates, method="da") # Dembinski, Abdelmotteleb
        m = Minuit(c, *truth)
        # m.fixed["x0"]=True
        m.migrad()
        m.hesse()
        r = m.fmin.reduced_chi2
        RChi2 = np.append(RChi2,r)
        MuB = np.append(MuB,m.values[0])
        MuS = np.append(MuS,m.values[1])

    print(m.params)
    avg = np.append(avg,np.sort(MuS)[950])


# print(f"\u03bc = {np.mean(avg):.0f} +- {np.std(avg):.0f}")

    
# print(f"max reduced Chi2: {max(RChi2):.2f}")
# print(f"min reduced Chi2: {min(RChi2):.2f}")
# print(f"avg reduced Chi2: {np.mean(RChi2):.2f}") 

fig, ax = plt.subplots(2, 2, figsize=(15, 5))

ax[0,0].hist(MuB,bins=24,histtype="bar",color="royalblue",label="Background Yield",edgecolor="black")

bin_content_S = ax[0,1].hist(MuS,bins=24,histtype="bar",color="darkorange",label="Signal Yield",edgecolor="black")
CL = np.sort(MuS)[int(num_runs*0.95)]
ax[0,1].vlines(CL,0,max(bin_content_S[0]),color="darkorange",label=f"95% CL = {CL:.0f}",linestyles="dashed")

ax[1,0].stairs(n,xe,fill=True, color="k", alpha=0.5,label="data")

RChiMean = np.mean(RChi2)
bin_content_RC = ax[1,1].hist(RChi2,bins=24,histtype="bar",color="blueviolet",label="Reduced Chi2",edgecolor="black")
ax[1,1].vlines(RChiMean,0,max(bin_content_RC[0]),color="blueviolet",label=f"\u03bc = {RChiMean:.2f}",alpha=0)
# for i, ti in enumerate(templates):
#   ax[1,1].stairs(ti, xe, fill=True, alpha=0.5, label=f"template {i+1}")

ax[0,0].legend()
ax[0,1].legend()
ax[1,0].legend()
ax[1,1].legend()

plt.show()
>>>>>>> 81d2f3aa7e0571b991b6cd0f3f13832801021b22
