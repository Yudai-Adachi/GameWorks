﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerHitSound : MonoBehaviour
{

    public AudioClip sound;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

private void OnCollisionEnter(Collision collision)
    {
        AudioSource.PlayClipAtPoint(sound, transform.position);
    }
}
