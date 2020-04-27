using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class image_alpha : MonoBehaviour {


    public float alpha = 0.5f;

	// Use this for initialization
	void Start () {
        var image = GetComponent<Image>();
        var color = image.color;
        color.a = alpha;
        image.color = color;
	}
	
	// Update is called once per frame
	void Update () {
		
	}
}
