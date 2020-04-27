using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraCircleManager : MonoBehaviour {

    [SerializeField] private bool findPlayer;
    private GameObject player;

    // Use this for initialization
    void Start() {
        findPlayer = false;
        player = GameObject.FindGameObjectWithTag("Player");
        foreach (Transform child in this.transform)
        {
            child.gameObject.GetComponent<SpriteRenderer>().enabled = false;
        }
	}

    // Update is called once per frame
    void Update() {
        if (player.GetComponent<Player>().isSmelling)
        {
            foreach (Transform child in transform)
            {
                child.gameObject.GetComponent<SpriteRenderer>().enabled = true;
            }
        }
        else
        {
            foreach (Transform child in transform)
            {
                child.gameObject.GetComponent<SpriteRenderer>().enabled = false;
            }
        }
	}
}
