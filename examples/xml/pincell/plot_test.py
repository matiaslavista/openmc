import openmc.core
from openmc.core import PlotBase, PlotBasis
from matplotlib import pyplot as plt

pb = PlotBase()
pb.origin = (0.0, 0.0, 230.0)
pb.width.x = 482.6
pb.width.y = 482.6
pb.pixels[0] = 1000
pb.pixels[1] = 1000
pb.basis = PlotBasis.xy
openmc.core.init()
data = pb.get_id_map()
data
plt.imshow(data[:,:,0])
plt.show()


