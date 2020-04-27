using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MoveCircle : MonoBehaviour {

    public float speed;
    public List<Vector2> toPositions2D;
    public int nextPosIndex;
    private Vector3 targetPosition;
    private GameObject player;
    private SpriteRenderer sr;
    private bool isHit;
    private float invincibleTime = 0.0f;
    private float INVINCIBLE_TIME_LIMIT = 5.0f;
    public enum CIRCLE_MODE {
        STOP,
        MOVE,
        FLASH
    }
    public CIRCLE_MODE mode = CIRCLE_MODE.STOP;

    // Use this for initialization
    void Start() {
        player = GameObject.FindGameObjectWithTag("Player");
        sr = gameObject.GetComponent<SpriteRenderer>();
        sr.enabled = false;
        invincibleTime = 0.0f;
    }

    // Update is called once per frame
    void Update() {
        //可視化
        if (player.GetComponent<Player>().isSmelling) {
            sr.enabled = true;
        }
        else
        {
            sr.enabled = false;
        }
        //当たり判定
        checkPlayerInCircle();
        switch (mode)
        {
            case CIRCLE_MODE.STOP:
                break;
            case CIRCLE_MODE.MOVE:
                move();
                break;
            case CIRCLE_MODE.FLASH:
                //flash();
                break;
        }
        move();
    }

    void move() {
        //移動先更新
        if (toPositions2D.Count != 0)
        {
            if (transform.position.x == toPositions2D[nextPosIndex].x && transform.position.z == toPositions2D[nextPosIndex].y)
            {
                if (toPositions2D.Count - 1 > nextPosIndex)
                {
                    nextPosIndex++;
                }
                else
                {
                    nextPosIndex = 0;
                }
            }
            targetPosition.x = toPositions2D[nextPosIndex].x;
            targetPosition.y = transform.position.y;
            targetPosition.z = toPositions2D[nextPosIndex].y;
            //移動
            transform.position = Vector3.MoveTowards(transform.position, targetPosition, speed * Time.deltaTime);
        }
    }
    void flash() {
        if(toPositions2D.Count != 0)
        {
            if (transform.position.x == toPositions2D[nextPosIndex].x && transform.position.z == toPositions2D[nextPosIndex].y)
            {
                if (toPositions2D.Count - 1 > nextPosIndex)
                {
                    nextPosIndex++;
                }
                else
                {
                    nextPosIndex = 0;
                }
            }
            targetPosition.x = toPositions2D[nextPosIndex].x;
            targetPosition.y = transform.position.y;
            targetPosition.z = toPositions2D[nextPosIndex].y;
            //瞬間移動


        }
    }
    void checkPlayerInCircle() {

        if (!isHit)
        {
            float circleRadian = gameObject.GetComponent<SpriteRenderer>().size.x / 2;
            Vector2 circleCenter = new Vector2(this.transform.position.x, this.transform.position.z);
            if ((player.GetComponent<Player>().position2D - circleCenter).sqrMagnitude < Mathf.Pow(circleRadian, 2))
            {
                player.GetComponent<Player>().HP -= 1;
                isHit = true;
            }
        }
        else {
            invincibleTime += Time.deltaTime;
            if(invincibleTime > INVINCIBLE_TIME_LIMIT)
            {
                isHit = false;
                invincibleTime = 0.0f;
            }
        }
        


    }
}
