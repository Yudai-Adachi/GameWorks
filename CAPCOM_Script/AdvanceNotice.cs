using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class AdvanceNotice : MonoBehaviour
{
    [SerializeField] GameObject[] foodPrefab;
    [SerializeField] Camera cam;
    [SerializeField] float spinSpeed;
    [SerializeField] float scale = 10.0f;

    GameObject nextFood;
    // Start is called before the first frame update
    void Start()
    {
        nextFood = foodPrefab[0];

        CreateNextNotice();
    }

    // Update is called once per frame
    void Update()
    {
        transform.Rotate(0.0f, spinSpeed * Time.deltaTime, 0.0f);
    }

    public void SetNextFood()
    {
        int i = Random.Range(0, foodPrefab.Length);
        nextFood = foodPrefab[i];
        if (this.transform.childCount == 0)
        {
            return;
        }
        //delete current object
        Destroy(this.transform.GetChild(0).gameObject);
        CreateNextNotice();
    }

    public GameObject GetNextObject()
    {
        return nextFood;
    }

    private void CreateNextNotice()
    {
        GameObject item = Instantiate(nextFood, transform.position, Quaternion.identity) as GameObject;
        item.transform.parent = this.transform;
        item.GetComponent<Rigidbody>().useGravity = false;
        item.transform.localScale = new Vector3(scale, scale, scale);
    }
}
