using System.Collections;
using System.Collections.Generic;
using UnityEngine;
/*
public class SensorSystem : MonoBehaviour {

    private GameObject player;
    private Transform razorSwitch;
    private Vector2 switchPosition;
    [SerializeField] private float switchResponceDistance = 2.0f;
    [SerializeField ]private bool isRazorActive;
	// Use this for initialization
	void Start () {
        razorSwitch = this.transform.Find("Switch");
        switchPosition = new Vector2(razorSwitch.transform.position.x, razorSwitch.transform.position.z);
        player = GameObject.FindGameObjectWithTag("Player");
        
	}
	
	// Update is called once per frame
	void Update () {

        if ((player.GetComponent<Player>().position2D - switchPosition).sqrMagnitude < Mathf.Pow(switchResponceDistance, 2)) {
            if (player.GetComponent<Player>().doAction) {
                foreach (var razor in GameObject.FindGameObjectsWithTag("Razor")) {
                    isRazorActive = !isRazorActive;
                    razor.GetComponent<LineRenderer>().enabled = !razor.GetComponent<LineRenderer>().enabled;
                }
                player.GetComponent<Player>().doAction = false;
            }
        }

	}
}*/
