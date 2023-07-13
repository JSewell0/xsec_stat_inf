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
