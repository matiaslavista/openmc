# coding: utf-8
import openmc.capi
from openmc.capi.plot import id_map, _PlotBase
from matplotlib import pyplot as plt

pb = _PlotBase()
pb.origin = (0, 0, 230.0)
pb.height = 482.6
pb.width = 482.6
pb.v_res = 1000
pb.h_res = 1000
pb
pb.basis = 'xy'
pb
openmc.capi.init([])
data = id_map(pb)
data
plt.imshow(data[:,:,0])
plt.show()
