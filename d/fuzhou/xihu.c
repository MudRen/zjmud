// Room: /d/fuzhou/xihu.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
��������ԭΪ����迣֮�����򣬻�һ��֮ˮ��Ϊ��ũ
ʱ�����񣬴�ˮ���̵�������Ϸ���㣬����ʮ�־��¡�
LONG );
	set("exits", ([
		"south" : __DIR__"ximendajie",
	]));
	set("outdoors", "fuzhou");
	setup();
}

