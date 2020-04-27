using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovewallController : MonoBehaviour
{
	public float mv_spd;    // 平行移動速度
	public float rotate_spd;    // 回転速度

	[SerializeField] private bool isMove; // 平行移動するか
	[SerializeField] private bool isRotate; // 回転するか

	// Start is called before the first frame update
	void Start()
	{

	}

	// Update is called once per frame
	void Update()
	{
		if (isMove)
		{
			// 平行移動 : WASD
			if (Input.GetKey(KeyCode.W))
			{
				transform.Translate(0, 0, mv_spd, Space.World);
			}
			if (Input.GetKey(KeyCode.S))
			{
				transform.Translate(0, 0, -1 * mv_spd, Space.World);
			}
			if (Input.GetKey(KeyCode.D))
			{
				transform.Translate(mv_spd, 0, 0, Space.World);
			}
			if (Input.GetKey(KeyCode.A))
			{
				transform.Translate(-1 * mv_spd, 0, 0, Space.World);
			}
		}

		if (isRotate)
		{
			// 角度変更 : 十字キー
			if (Input.GetKey(KeyCode.UpArrow))
			{
				transform.Rotate(-1 * rotate_spd, 0, 0);
			}
			if (Input.GetKey(KeyCode.DownArrow))
			{
				transform.Rotate(rotate_spd, 0, 0);
			}
			if (Input.GetKey(KeyCode.RightArrow))
			{
				transform.Rotate(0, rotate_spd, 0, Space.World);
			}
			if (Input.GetKey(KeyCode.LeftArrow))
			{
				transform.Rotate(0, -1 * rotate_spd, 0, Space.World);
			}
		}		
	}
}
