//Room: /d/foshan/northgate.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
	set("short","����");
	set("long",@LONG
�����Ƿ�ɽ��ı��š��������򱱣���������ɴ���ԭ������
һ��������Ĵ���Ƿ�ɽ�����Ҫ�ֵ���
LONG);
	set("outdoors", "foshan");
	set("exits",([ /* sizeof() == 1 */
	    "south"  : __DIR__"street3",
	    "north"  : __DIR__"nanling",
	]));
	setup();
}

