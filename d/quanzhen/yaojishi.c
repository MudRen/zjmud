// yaojishi.c ҩ����
// By Lgg,1998.10

inherit ROOM;
int do_pullout(string arg);

void create()
{
	set("short", "ҩ����");
	set("long", @LONG
������ȫ�����ҩ����ҩ�ĵط�����䷿�䱾���ܴ�ֻ��
��ǰ�����Ҷѷŵ�ҩ��ҩ�伷���Ե�С���ˡ�ҩ���Ѿ��ܳ¾��ˣ�
���������Ϻõ��Ϻ�����ľ���ɵģ���˵������ľ�����ɵĹ���
�������ض��������������
LONG
	);
	set("sleep_room",1);
	set("exits", ([
		"east" : __DIR__"xianzhentang",
	]));

	set("objects", ([
		__DIR__"npc/zhangyao" : 1,
	]));

	setup();
}

