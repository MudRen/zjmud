// Room: /d/fuzhou/wuyishan6.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�������ֳ�ɴñ�壬ɽ�������ɴñ���������Ƕ���������
�����±������Ϸ������������ۻ롣ԶԶ��ȥ���������������
����Ůңң������ʯ���Ͽ��С��Ӹ�˼Σ�����֡�
LONG );
	set("exits", ([
		"southdown" : __DIR__"wuyishan2",
	]));
	set("outdoors", "fuzhou");
	setup();
}

