using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
// using System; // ��� ����

public class Test : MonoBehaviour
{
    public TextMeshProUGUI text;

    int Add(int a, int b)
    {
        return a + b;
    }

    // Start is called before the first frame update -- ������ �� �ѹ�
    void Start()
    {
        text.SetText("hahahaha");
        int result = Add(1, 5);
        Debug.Log(result);

        int i = 10;
        string a = "hi";
        float b = 3.5f;

        int[] array = new int[10];

        array[0] = 1;
        array[1] = 2;
        array[2] = 3;
        array[3] = 4;

        Debug.Log("Hello word" + i + a + b);
        // Console.WriteLine("I am C#");

        for(int j = 0; j < 4; j++)
        {
            if(j < 2)
            {
                Debug.Log(array[j]);
            }
        }

        switch (i)
        {
            case 10:
                Debug.Log("inside switch");
                break;
        }
    }

    // Update is called once per frame -- ������ �ݺ�
    void Update()
    {
        
    }
}
