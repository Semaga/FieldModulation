import matplotlib.pyplot as plt
import numpy as np

def PlotData(EFS_OutputFile, Title = "EFS", dispertion = False ,Scale=True):
    """
    PlotData(filename, Title, Scale=True):
    """
    with open(EFS_OutputFile) as read:
        read.readline()
        a = read.readline()
        a = a.split()
        lenght_x = float(a[2])
        a = read.readline()
        a = a.split()
        lenght_y = float(a[2])
        a = read.readline()
        a = a.split()
        dimensional = int(a[2])
        a = read.readline()
        a = a.split()
        NumberOfParticle = int(a[1])
        pos = np.zeros((NumberOfParticle, 2), float)
        pos_z = np.zeros((NumberOfParticle), float)
        for i in range(NumberOfParticle):
            read.readline()
            a = read.readline()
            a = a.split()
            position_x = float(a[2])
            a = read.readline()
            a = a.split()
            position_y = float(a[2])           
            a = read.readline()
            a = a.split()
            position_z = float(a[2])
            a = read.readline()
            a = a.split()
            Charge = float(a[2])
            pos[i] = position_x, position_y
            pos_z[i] = position_z
        if dispertion:   
            for line in read:
                if line == "Data:\n":
                    a = read.readline()

    if dispertion:
        a = a.split()

        data = np.zeros((dimensional, dimensional), float)

        for i, value in enumerate(a):
            a[i] = float(value)

        i = 0
        j = 0
        for k, value in enumerate(a):
            i = int(k%dimensional)
            j = int(k/dimensional)
            data[i][j] = float(value)


        X = np.linspace(0, lenght_x, dimensional)
        Y = np.linspace(0, lenght_y, dimensional)
    

    plt.figure(figsize = (lenght_x*1000, lenght_y*1000))
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Position charge particle in XY-plane")
    x = [0, lenght_x]
    y = [0, 0]
    plt.plot(x, y, linewidth=2, c = 'red')
    x = [0, lenght_x]
    y = [lenght_y, lenght_y]
    plt.plot(x, y, linewidth=2, c = 'red') 
    x = [0, 0]
    y = [0, lenght_y]
    plt.plot(x, y, linewidth=2, c = 'red')
    x = [lenght_x, lenght_x]
    y = [0, lenght_y]
    plt.plot(x, y, linewidth=2, c = 'red')
    for i in pos:
        plt.scatter(i[0],i[1], color = 'b')
    plt.show()

    plt.figure()
    plt.title('Dispertion particle along Z-axis')
    plt.xlabel('Particle')
    plt.ylabel('Position along z-axis')
    plt.ylim(0, 0.00000065)
    for i, value in enumerate(pos_z):
        plt.scatter(i, value, color = 'black')
    plt.show()

    if dispertion:           
        fig, ax = plt.subplots(constrained_layout = True)
        ax.set_title(Title)
        if Scale:
            CS = ax.contourf(X, Y, np.log(data), 100, origin = 'lower')
        else:
            CS = ax.contourf(X, Y, (data), 100, origin = 'lower')

        ax.set_xlabel('X')
        ax.set_ylabel('Y')
        cbar = fig.colorbar(CS)
        cbar.ax.set_ylabel('Value of ln(E)')
        plt.show()