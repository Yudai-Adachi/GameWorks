using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Title : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        //StartCoroutine("Adjustment");
    }

    // Update is called once per frame
    void Update()
    {
    }

    private void OnDestroy()
    {
        SceneManager.LoadScene("PinchingSandbox");
    }

    /*
    IEnumerator Adjustment()
    {
        yield return new WaitForSeconds(1.0f);
        SceneManager.LoadScene("PinchingSandbox");
    }
    */
}
