using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JammerController : MonoBehaviour
{
	[SerializeField] private bool isX; // X軸移動するか
	[SerializeField] private bool isY; // Y軸移動するか
	[SerializeField] private bool isZ; // Z軸移動するか

	[SerializeField] private float spd; // オブジェクトの移動速度

	[SerializeField] private float revTime; // 折り返すまでの秒数

	private Vector3 dir = new Vector3 (0, 0, 0);
	private float now = 0f;

	// Start is called before the first frame update
	void Start()
	{
		if (isX) dir += new Vector3(1, 0, 0);
		if (isY) dir += new Vector3(0, 1, 0);
		if (isZ) dir += new Vector3(0, 0, 1);
	}

	// Update is called once per frame
	void Update()
	{
		transform.position += dir * spd;
		now += Time.deltaTime;
		if(now >= revTime)
		{
			now = 0f;
			dir *= -1;
		}
		
	}
}
