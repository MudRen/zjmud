// liangong.c ��������
// Java Oct.10 1998

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
����ʯ����״�������أ�ǰխ�����Ϊ���Σ����߰�Բ������
ȴ��������״��ԭ��������ǰ������ʦ�������ң�ǰխ���ƣ����ʹ
ȭ����Բ�н������Ƿ��ڡ������и�С�Ŷ���ͨ������������ҡ�
LONG
	);

	set("exits", ([
		"east"  : __DIR__"zhengting",
		"south" : __DIR__"liangong2",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4,
	]));
	set("for_family", "��Ĺ��");
	setup();
}
