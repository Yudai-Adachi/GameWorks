using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyVanish : MonoBehaviour
{

    GameObject player;
    SkinnedMeshRenderer[] bodyRenderers;
    
    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        bodyRenderers = GetComponentsInChildren<SkinnedMeshRenderer>();
        Debug.Log(bodyRenderers.Length);
    }

    // Update is called once per frame
    void Update()
    {
        if (player.GetComponent<Player>().isSmelling)
        {
            foreach(var br in bodyRenderers)
            {

                br.enabled = false;
            }
        }
        else
        {
            foreach (var br in bodyRenderers)
            {

                br.enabled = true;
            }
        }
        
    }
}
