// liangong2.c ��������

inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
����ʯ����״�������أ�ǰխ�����Ϊ���Σ����߰�Բ������
ȴ��������״��ԭ��������ǰ������ʦ�������ң�ǰխ���ƣ����ʹ
ȭ����Բ�н������Ƿ��ڡ������и�С�Ŷ���ͨ������������Һ͹�
Ĺ�ڲ���������һ��Сʯ�ҡ�
LONG
	);

	set("exits", ([
		"north" : __DIR__"liangong",
		"south" : __DIR__"liangong3",
	]));
	set("objects", ([
		"/clone/npc/mu-ren" : 4,
	]));
	set("for_family", "��Ĺ��");
	setup();
}
