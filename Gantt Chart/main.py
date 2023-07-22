import pandas as pd
import matplotlib.pyplot as plt
import functions as c


df = pd.DataFrame(
    c.formatAsDataFrame_5(
        c.calculateTimeToStart_4(
            c.findHiddenDependency_3(
                c.convertToDictionary_2(
                    c.takeInputTable_1()
                )
            )
        )
    )
)

plt.barh(y=df['task'], width=df['duration'], left=df['time_to_start'])
plt.title('Project Management Schedule', fontsize=15)
plt.show()


