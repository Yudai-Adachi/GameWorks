using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Title : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        _Use = false;
    }

    // Update is called once per frame
    void Update()
    {

    }

    private bool _Use = false;

    private void OnCollisionEnter(Collision collision)
    {
        if (_Use)
        {
            return;
        }
        GetComponentInChildren<SpriteRenderer>().color = new Color(1.0f, 0.5f, 0.0f, 0.0f);
        transform.GetChild(0).gameObject.active = true;

        Manager.SceneMoveManager.Instance.Test = true;
       // Manager.SceneMoveManager.Instance.SetNextScene(Manager.SceneMoveManager.SceneType.Game);
        _Use = true;
    }

}
