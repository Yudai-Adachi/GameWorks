using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class EnemyAI : MonoBehaviour {


    public float walkSpeed = 0.0f;//移動速度
    private float runSpeed = 1.5f;//疾走速度

    [SerializeField] private Vector2 position2D;//2次元座標
    private GameObject player;//プレイヤー情報
    public List<Vector2> toPosition2Ds;//目的地一覧(2次元) 
    [SerializeField] private int toPositionIndex;//目的地インデックス
    public int initIndex;
    private Vector3 targetPosition;//目的地
    public bool findPlayer = false;
    public bool hitPlayer = false;
    [SerializeField] private float invincibleTime = 0.0f;
    private float INVINCIBLE_LIMIT_TIME = 2.8f;
    [SerializeField] private float chasingTime = 0.0f;
    private float CHASING_LIMIT_TIME = 8.0f;

    public enum ENEMY_MODE {//敵状態
        STAND,//棒立ち
        PATROL,//巡回
        CHASE,//追跡
    }
    [SerializeField] private ENEMY_MODE mode;//状態
    private ENEMY_MODE priviousMode;
    public ENEMY_MODE initMode = ENEMY_MODE.STAND;//初期状態
    Animator animator;
    NavMeshAgent navMeshAgent;


	// Use this for initialization
	void Start () {
        
        position2D.x = this.transform.position.x;
        position2D.y = this.transform.position.z;
        player = GameObject.FindGameObjectWithTag("Player");
        animator = gameObject.GetComponent<Animator>();
        navMeshAgent = GetComponent<NavMeshAgent>();
        navMeshAgent.speed = walkSpeed;
        toPositionIndex = initIndex;
        mode = initMode;
	}
	

	// Update is called once per frame
	void Update () {
        //2d座標更新
        position2D.x = this.transform.position.x;
        position2D.y = this.transform.position.z;

        //行動
        switch (mode) {
            case ENEMY_MODE.STAND:
                animator.SetBool("LookAround", true);
                animator.SetBool("Run", false);
                animator.SetBool("Walk", false);
                navMeshAgent.isStopped = true;
                targetPosition = this.transform.position;
                if (navMeshAgent.pathStatus != NavMeshPathStatus.PathInvalid)
                {
                    navMeshAgent.SetDestination(targetPosition);
                }
                //発見
                if (findPlayer)
                {
                    navMeshAgent.isStopped = false;
                    priviousMode = mode;
                    mode = ENEMY_MODE.CHASE;
                }
                break;

            case ENEMY_MODE.PATROL:
                animator.SetBool("Walk", true);
                animator.SetBool("Run", false);
                animator.SetBool("LookAround", false);
                Patrol();
                if (findPlayer) {
                    priviousMode = mode;
                    mode = ENEMY_MODE.CHASE;
                }
                break;

            case ENEMY_MODE.CHASE:
                animator.SetBool("Run", true);
                animator.SetBool("LookAround", false);
                animator.SetBool("Walk", false);
                Chase();
                if (!findPlayer) {
                    mode = priviousMode;
                }
                break;
        }
	}

    //巡回
    void Patrol()
    {
        if (toPosition2Ds.Count != 0)
        {
            //移動先更新
            if (Mathf.Abs(position2D.x - targetPosition.x) < 0.25f && Mathf.Abs(position2D.y - targetPosition.z) < 0.25f)
            {
                if (toPosition2Ds.Count - 1 > toPositionIndex)
                {
                    toPositionIndex++;
                }
                else
                {
                    toPositionIndex = 0;
                }

            }
            targetPosition.x = toPosition2Ds[toPositionIndex].x;
            targetPosition.y = transform.position.y;
            targetPosition.z = toPosition2Ds[toPositionIndex].y;
            if (navMeshAgent.pathStatus != NavMeshPathStatus.PathInvalid)
            {
                navMeshAgent.SetDestination(targetPosition);
            }
            else
            {
                Debug.Log("error");
            }
        }
    }

    //追跡
    void Chase() {     
        navMeshAgent.speed = runSpeed;
        if (navMeshAgent.pathStatus != NavMeshPathStatus.PathInvalid)
        {
            navMeshAgent.SetDestination(player.transform.position);
        }

        //プレイヤーに衝突で停止
        if (hitPlayer)
        {
            navMeshAgent.isStopped = true;
            invincibleTime += Time.deltaTime;
            //無敵時間
            if (invincibleTime > INVINCIBLE_LIMIT_TIME) {
                invincibleTime = 0.0f;
                hitPlayer = false;
                navMeshAgent.isStopped = false;
            }
        }
        //発見で追跡
        else if (findPlayer)
        {
            chasingTime += Time.deltaTime;
            //追跡時間
            if(chasingTime > CHASING_LIMIT_TIME)
            {
                chasingTime = 0.0f;
                findPlayer = false;
            }
        }
        else {
            if (navMeshAgent.pathStatus != NavMeshPathStatus.PathInvalid)
            {
                navMeshAgent.SetDestination(targetPosition);

            }
        }
    }



    private void OnCollisionEnter(Collision collision)
    {
        if (!hitPlayer)
        {
            if (collision.gameObject.tag == "Player")
            {
                hitPlayer = true;
                player.GetComponent<Player>().HP -= 1;
                if (!findPlayer)
                {
                    findPlayer = true;
                }
            }

        }

    }
}
