using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class FindPlayer : MonoBehaviour {

    public float sightRadius;//球半径
    public float sightMaxDistance;//最大距離

	// Use this for initialization
	void Start () {
        sightRadius = 0.5f;
        sightMaxDistance = 5.0f;
	}
	
	// Update is called once per frame
	void Update () {
        Search();
	}

    //
    bool Search()
    {
        bool canFindPlayer = false;
        RaycastHit hitInfo;//衝突オブジェクトの情報
        //Physics.BoxCast(Vector3 center, Vector3 halfExtents, Vector3 direction, out RaycastHit hitInfo, Quaternion orientation, float maxDistance);
        //Physics.CapsuleCast(Vector3 point1, Vector3 point2, float radius, Vector3 direction, out RaycastHit hitInfo, float maxDistance);
        //Physics.Linecast((Vector3 start, Vector3 end, out RaycastHit hitInfo);
        //Physics.Raycast(Vector3 origin, Vector3 direction, out RaycastHit hitInfo, float maxDistance);
        //Physics.SphereCast(origing radius, direction, hitInfo, maxDistance);
        if (Physics.SphereCast(this.transform.position, sightRadius, this.transform.forward, out hitInfo, sightMaxDistance))
        {
            if (hitInfo.collider.CompareTag("Player"))
            {
                Debug.Log("Player");
                canFindPlayer = true;
            }
            else
            {
                Debug.Log("Not Player");
            }
        }
        else {
            Debug.Log("No Object");
        }
        return canFindPlayer;
    }

    //SphereCast可視化(デバッグ用)
    private void OnDrawGizmos()
    {
        RaycastHit hitInfo;
        if (Physics.SphereCast(this.transform.position, sightRadius, this.transform.forward, out hitInfo, sightMaxDistance))
        {
            Gizmos.DrawRay(this.transform.position, this.transform.forward * hitInfo.distance);
            Gizmos.DrawWireSphere(this.transform.position + this.transform.forward * hitInfo.distance, sightRadius);
        }
        else {
            Gizmos.DrawRay(this.transform.position, this.transform.forward * sightMaxDistance);
        }
    }
}


