using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Launcher : MonoBehaviour
{
    [SerializeField] float reLaunchTime = 100.0f;
    [SerializeField] float rotateSpeed = 1.0f;
    [SerializeField] float spd;
    [SerializeField] Camera cam;
    [SerializeField] bool random;
    [SerializeField] Vector3 direction;
    [SerializeField] float padding=40.0f;
    [SerializeField] Vector3 targetPosOffset;


    float elapsedTime = 0.0f;
    const float maxRotX = 45.0f;
    const float maxRotY = 45.0f;
    const float minRotX = -45.0f;
    const float minRotY = -45.0f;

    Vector3 rot = new Vector3(0.0f, 0.0f, -10.0f);

    bool rotFlg = false;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        elapsedTime += Time.deltaTime;
        if (rotFlg == false && (++elapsedTime) > reLaunchTime)
        {
            rotFlg = true;
            elapsedTime = 0.0f;

            //calculate lookatrotation
            Vector3 viewPos = cam.WorldToViewportPoint(transform.position);
            rot.x = Random.Range(cam.transform.position.x - padding - viewPos.x/2, cam.transform.position.x + padding - viewPos.x/2);
            rot.y = Random.Range(0.0f, cam.transform.position.y + padding - viewPos.y);
           
            //rot.z = cam.transform.position.z; 
            rot += targetPosOffset;
        }
        else if (rotFlg == true)
        {
            Vector3 dir = (rot - transform.position).normalized;
            float dot = Vector3.Dot(dir, transform.forward);
            if (dot > 0.995f)
            {
                Debug.Log("yeah");
                shoot();
                rotFlg = false;
            }
            else
            {
                transform.rotation = Quaternion.Lerp(transform.rotation, Quaternion.LookRotation(dir), rotateSpeed * Time.deltaTime);
                //Quaternion.Slerp(transform.rotation, Quaternion.Euler(new Vector3(rot.x, rot.y, 0.0f)), rotateSpeed * Time.deltaTime);          
            }
        }
        //Debug.Log(transform.forward);
    }

    //private void rotate()
    //{
    //    float lhsX = transform.localEulerAngles.x - minRotX;
    //    float rhsX = Mathf.Abs(transform.localEulerAngles.x - maxRotX);
    //    float lhsY = transform.localEulerAngles.y - minRotY;
    //    float rhsY = Mathf.Abs(transform.localEulerAngles.y - maxRotY);

    //    float RotX = Random.Range(lhsX, rhsX);
    //    float RotY = Random.Range(lhsY, rhsY);

    //    transform.rotation = Quaternion.Slerp(transform.rotation, Quaternion.Euler(new Vector3(RotX, RotY, 0.0f)), rotateSpeed * Time.deltaTime);
    //}
    //Vector3.Angle (fromVector, toVector);
    void shoot()
    {
        GameObject nextFood = GetComponentInChildren<AdvanceNotice>().GetNextObject();
        GameObject item = Instantiate(nextFood, transform.position, Quaternion.identity) as GameObject;
        if(random)
        {
            item.GetComponent<Rigidbody>().velocity = transform.forward * spd;
        }
        else
        {
            item.GetComponent<Rigidbody>().velocity = direction;
        }

        //角速度を設定
        Vector3 angleVec = Vector3.left * Random.Range(-Mathf.PI * 2.0f, Mathf.PI * 2.0f);
        angleVec += Vector3.up * Random.Range(-Mathf.PI * 2.0f, Mathf.PI * 2.0f);
        angleVec += Vector3.forward * Random.Range(-Mathf.PI * 2.0f, Mathf.PI * 2.0f);
        item.GetComponent<Rigidbody>().angularVelocity = angleVec;
        
        GetComponentInChildren<AdvanceNotice>().SetNextFood();
    }

    // 乱射
    public void SetPadding(float in_padding)
    {
        padding = in_padding;
    }

    //　発射スピード
    public void SetLaunchTime(float in_LaunchTime)
    {
        reLaunchTime = in_LaunchTime;
    }

    //　乱射時曲がるスピード
    public void SetRotSpd(float in_RotSpd)
    {
        rotateSpeed = in_RotSpd;
    }
}
