// Room: /d/fuzhou/fzroad10.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�Ƶ��ſ�һ�������Ӱ����ӹ��ţ��������ϲ�ȴ�����ˡ���
��é�ݵ�С���Ե�ʮ�ֿ��䣬ֻ��һ���������ẩ�ӿ��ھ�¯��
����������㡣
LONG );
	set("exits", ([
		"south"     : __DIR__"fzroad9",
	]));
	set("objects", ([
		"/d/qingcheng/npc/yuyan" : 1,
	]));
	set("outdoors", "fuzhou");
	setup();
}

