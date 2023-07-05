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

def generate(sr, rng):
    
    bN = np.array([])
    xe = np.array([])
    
    if sr == "WH":
        bN = np.array([34.9,16.2,5.2,3.1,2.9,1.29,1.19,1.02])
        xe = np.array([200,250,300,350,400,450,500,600,1000])
    elif sr == "W":
        bN = np.array([749.4,332.4,176.4,99.4,60.7,34.7,26.9,18.8,3.5])
        xe = np.array([200,250,300,350,400,450,500,600,800,1000])    
    elif sr == "H":
        bN = np.array([1244,555,311,156,93,77.1,55.8,30.2,7.5])
        xe = np.array([200,250,300,350,400,450,500,600,800,1000])      

    n = rng.poisson(bN) 
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

sr = "WH"
hist_name = "TChiWH_"+sr+"SR_1000_100"
sT = get_template(hist_name)

for x in range(1000):
    
  rng = np.random.default_rng()
  xe, n, bT = generate(sr, rng)
  templates = np.array([bT,sT])
  truth = bT.sum(), sT.sum()

  c = Template(n, xe, templates, method="da") # Dembinski, Abdelmotteleb
  m = Minuit(c, *truth)
  m.migrad()
  m.hesse()

  r = m.fmin.reduced_chi2

  RChi2 = np.append(RChi2,r)
  MuB = np.append(MuB,m.values[0])
  MuS = np.append(MuS,m.values[1])

print(f"max reduced Chi2: {max(RChi2):.2f}")
print(f"min reduced Chi2: {min(RChi2):.2f}")
print(f"avg reduced Chi2: {np.mean(RChi2):.2f}") 

fig, ax = plt.subplots(2, 2, figsize=(15, 5))

ax[0,0].hist(MuB,bins=24,histtype="bar",color="royalblue",label="Background Yield",edgecolor="black")
bin_content = ax[0,1].hist(MuS,bins=24,histtype="bar",color="darkorange",label="Signal Yield",edgecolor="black")
ax[0,1].vlines(np.sort(MuS)[950],0,max(bin_content[0]),color="darkorange",label=f"95% CL = {np.sort(MuS)[950]:.0f}",linestyles="dashed")
ax[1,0].stairs(n,xe,fill=True, color="k", alpha=0.5,label="data")
for i, ti in enumerate(templates):
  ax[1,1].stairs(ti, xe, fill=True, alpha=0.5, label=f"template {i+1}")

ax[0,0].legend()
ax[0,1].legend()
ax[1,0].legend()
ax[1,1].legend()

plt.show()
