//Room: /d/foshan/road4.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","С��");
	set("long",@LONG
������һ���ּ�С���������������ѡ������ǹ����ˡ�����ɽ
��ï�ܣ�������棬��λ��·Ҫʮ��С�ġ�
LONG);
	set("objects", ([
	   "/clone/beast/dushe": 1,
	]));
	set("outdoors", "foshan");
	set("exits",([ /* sizeof() == 1 */
	    "southwest" : __DIR__"road3",
	    "southeast" : __DIR__"road5",
	]));

	set("resource/snake", ({ "/clone/beast/jinshe",
				 "/clone/beast/wubushe",
				 "/clone/beast/qingshe", }));

	setup();
}
