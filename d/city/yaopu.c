// Room: /city/yaopu.c
inherit ROOM;

void create()
{
	set("short", "ҩ��");
	set("long", @LONG
����һ��ҩ�̣�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵļ��ٸ�С
������ɢ�������ġ���ҽƽһָ���ڲ輸�ԣ����Ժ��Ų裬��Ҳ������һ�ۡ�
��̨������һ�ŷ��ƵĹ�档
LONG );
	set("item_desc", ([
		"����桿" : "�����������ҩƷ��
��ҩ��\tʮ������
����ҩƷ�������顣\n",
	]));
	set("objects", ([
		__DIR__"npc/ping" : 1,
		__DIR__"npc/huoji" : 1,
	]));
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([
		"south" : __DIR__"dongdajie2",
		"north" : __DIR__"yaopu_neishi",

	]));
	setup();
}
