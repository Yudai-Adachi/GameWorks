using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour {

    public int HP = 5;
    public float rotateSpeed = 10;
    public float moveSpeed = 700.0f;
    private float walkSpeed = 1.8f;
    private float runSpeed = 3.0f;
    private float crawlSpeed = 1.5f;
    private float rotationSpeed = 75.0f;
    private float jumpPower = 0.8f;
    private bool isCrawling;
    public bool isSmelling;
    public Vector2 position2D;
    private BoxCollider standCollider;
    private BoxCollider crawlCollider;
    private Animator animator;

    Vector3 targetDirection;
    Vector3 moveDirection = Vector3.zero;

    Rigidbody rb;


    // Use this for initialization
    void Start () {

        standCollider = gameObject.GetComponents<BoxCollider>()[1]; 
        crawlCollider = gameObject.GetComponents<BoxCollider>()[0];
        animator = gameObject.GetComponent<Animator>();
        rb = GetComponent<Rigidbody>();
        isCrawling = false;
        isSmelling = false;
       // doAction = false;
        position2D = new Vector2(transform.position.x, transform.position.z);
	}

    // Update is called once per frame
    void FixedUpdate()
    {

        //2次元座標更新
        position2D.x = transform.position.x;
        position2D.y = transform.position.z;

        //アクション
        if (Input.GetKeyDown(KeyCode.N))
        {
            //doAction = true;
        }
        else {
            //doAction = false;
        }

        //嗅覚モード
        if (Input.GetKeyDown(KeyCode.Space))
        {
            isSmelling = !isSmelling;

        }
        //匍匐判定
        if (Input.GetKeyDown(KeyCode.C))
        {
            isCrawling = !isCrawling;
            if (isCrawling)
            {
                animator.SetBool("CrawlingWait", true);
                standCollider.enabled = false;
                crawlCollider.enabled = true;
            }
            else {
                animator.SetBool("Crawl", false);
                animator.SetBool("CrawlingWait", false);
                standCollider.enabled = true;
                crawlCollider.enabled = false;
            }
        }

        //移動
        //匍匐
        /*
        if (isCrawling)
        {
            if (Input.GetKey(KeyCode.W))
            {
                //匍匐前進
                crawl();
                animator.SetBool("Crawl", true);
            }
            else
            {
                //匍匐待機
                animator.SetBool("Crawl", false);
            }
        }
        else
        {
            
            if (Input.GetKey(KeyCode.W))
            {
                //走る
                if (Input.GetKey(KeyCode.V))
                {
                    run();
                    animator.SetBool("Run", true);
                        
                }
                //歩く
                else {
                    //walk();
                    moveControl();
                    animator.SetBool("Walk", true);
                    animator.SetBool("Run", false);
                }
            }
            //待機
            else
            {
                //待機
                animator.SetBool("Walk", false);
                animator.SetBool("Run", false);
            }
            
        }
        */

        moveControl();
        RotationControl();
        //rb.AddForce(moveDirection * Time.deltaTime);
        transform.Translate((moveDirection * Time.deltaTime) / 1000,Space.World);
    }

    //歩く
    //void walk() {
    //    transform.Translate(transform.forward * walkSpeed * Time.deltaTime, Space.World);
    //}

    void moveControl()
    {
        float v = Input.GetAxisRaw("Vertical");                 //上下の入力
        float h = Input.GetAxisRaw("Horizontal");               //右左の入力

        Vector3 forward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1));
        Vector3 right = Camera.main.transform.right;

        targetDirection = h * right + v * forward;

        moveDirection = targetDirection * walkSpeed * moveSpeed;

        if (v > 0f || v < 0f || h > 0f || h < 0f)
        {
            if (isCrawling)
            {
                animator.SetBool("Crawl", true);
            }
            else if (Input.GetKey(KeyCode.E))
            {
                animator.SetBool("Run", true);
                moveSpeed = 1400.0f;
            }
            else
            {
                moveSpeed = 700.0f;
                animator.SetBool("Walk", true);
                animator.SetBool("Run", false);
            }
        }
        else
        {
            animator.SetBool("Walk", false);
            animator.SetBool("Run", false);
            animator.SetBool("Crawl", false);
        }
    }


    //這う
    void crawl() {
        transform.Translate(transform.forward * crawlSpeed * Time.deltaTime, Space.World);
    }

    void run()
    {
        transform.Translate(transform.forward * runSpeed * Time.deltaTime, Space.World);
    }

    void jump() {
        //rb.AddForce(this.transform.up * jumpPower, ForceMode.Impulse);
        animator.SetTrigger("Jump");
    }

    void RotationControl()
    {
        Vector3 rotateDirection = moveDirection;
        rotateDirection.y = 0;

        if (rotateDirection.sqrMagnitude > 0.01)
        {
            float step = rotateSpeed * Time.deltaTime;
            Vector3 newDir = Vector3.Slerp(transform.forward, rotateDirection, step);
            transform.rotation = Quaternion.LookRotation(newDir);
        }
    }

}


/*
void moveControl()
{
    float v = Input.GetAxisRaw("Vertical");                 //上下の入力
    float h = Input.GetAxisRaw("Horizontal");               //右左の入力

    Vector3 forward = Vector3.Scale(Camera.main.transform.forward, new Vector3(1, 0, 1));
    Vector3 right = Camera.main.transform.right;

    targetDirection = h * right + v * forward;


    if (controller.isGrounded)
    {
        moveDirection = targetDirection * speed;

        if (Input.GetButton("Jump"))
        {
            moveDirection.y = jumpspeed;
        }
    }
    else
    {
        float temp = moveDirection.y;
        moveDirection = Vector3.Scale(targetDirection, new Vector3(1, 0, 1)).normalized;
        moveDirection *= speed;
        moveDirection.y = temp - gravity * Time.deltaTime;
    }

    if (v > 0f || v < 0f || h > 0f || h < 0f)
    {
        animator.SetFloat("Speed", 1f);
        animator.SetBool("Running", true);
    }
    else
    {
        animator.SetFloat("Speed", 0f);
        animator.SetBool("Running", false);
    }
}
*/
