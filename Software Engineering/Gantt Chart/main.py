import pandas as pd
import matplotlib.pyplot as plt
import functions as c


df = pd.DataFrame(
    c.formatAsDataFrame_5(
        c.calculateTimeToStart_4(
            c.findHiddenDependency_3(
                c.convertToDictionary_2(
                    c.takeInput()
                )
            )
        )
    )
)

plt.barh(y=df['task'], width=df['duration'], left=df['time_to_start'], color='maroon')
plt.title('Project Management Schedule', fontsize=15)
plt.xlabel("<---- Time ---->")
plt.ylabel("<---- Tasks ---->")
plt.savefig("Graph_Outputs/graph.png")
plt.show()




