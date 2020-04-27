using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sight : MonoBehaviour
{
    float sightDistance = 3.0f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        RaycastHit hitInfo;
        Vector3 sightTarget = transform.position + transform.right * sightDistance;

        if (Physics.Raycast(transform.position, transform.right, out hitInfo, sightDistance))
        {
            if (hitInfo.collider.tag == "Player")
            {
                transform.root.GetComponent<EnemyAI>().findPlayer = true ;
            }
        }

    }
    //デバッグ用
    private void OnDrawGizmos()
    {
        Gizmos.DrawLine(this.transform.position, transform.position + transform.right * sightDistance);
    }
}
