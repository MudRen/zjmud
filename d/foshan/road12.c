//Room: /d/foshan/road12.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","�ּ��");
	set("long",@LONG
������һ���ּ�С���������������ѡ�����ɽ��ï�ܣ������
�棬��λ��·Ҫʮ��С�ġ�
LONG);
	set("objects", ([
	   "/clone/beast/dushe": 1,
	]));
	set("outdoors", "foshan");
	set("exits",([ /* sizeof() == 1 */
	    "northwest" : __DIR__"road10",
	]));

	set("resource/snake", ({ "/clone/beast/dushe", }));

	setup();
}

