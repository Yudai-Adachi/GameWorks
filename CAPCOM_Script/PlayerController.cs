using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
	public float mv_spd;	// 平行移動速度
	public float rotate_spd;    // 回転速度

	public bool isTitle; // タイトル画面かどうか

	// Start is called before the first frame update
	void Start()
	{
		
	}

	// Update is called once per frame
	void Update()
	{
		if (isTitle)
		{
			// 平行移動 : WASD
			if (Input.GetKey(KeyCode.W))
			{
				transform.Translate( 0, 0, mv_spd, Space.World);
			}
			if (Input.GetKey(KeyCode.S))
			{
				transform.Translate( 0, 0, -1 * mv_spd, Space.World);
			}
			if (Input.GetKey(KeyCode.D))
			{
				transform.Translate(mv_spd, 0, 0,  Space.World);
			}
			if (Input.GetKey(KeyCode.A))
			{
				transform.Translate(-1 * mv_spd, 0, 0, Space.World);
			}

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
		else
		{
			// 平行移動 : WASD
			if (Input.GetKey(KeyCode.W))
			{
				transform.Translate(-1 * mv_spd, 0, 0, Space.World);
			}
			if (Input.GetKey(KeyCode.S))
			{
				transform.Translate(mv_spd, 0, 0, Space.World);
			}
			if (Input.GetKey(KeyCode.D))
			{
				transform.Translate(0, 0, mv_spd, Space.World);
			}
			if (Input.GetKey(KeyCode.A))
			{
				transform.Translate(0, 0, -1 * mv_spd, Space.World);
			}

			// 角度変更 : 十字キー
			if (Input.GetKey(KeyCode.UpArrow))
			{
				transform.Rotate(0, 0, -1 * rotate_spd);
			}
			if (Input.GetKey(KeyCode.DownArrow))
			{
				transform.Rotate(0, 0, rotate_spd);
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
