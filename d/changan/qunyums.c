//Room: qunyums.c

inherit ROOM;

void create()
{
	set("short", "Ⱥ��¥����");
	set("long", @LONG
�������沼�õü򵥶�������Ȥ������ܿ��������ż��軨����
�ݣ�������䣬�������£�����������Ŀ��������һ��ʮ�����С����
���޸���ͣ���Ա�վ���ĸ����֡�
LONG);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"qunyuys8",
	]));
	set("objects", ([
		__DIR__"npc/dashou" : 4,
		__DIR__"npc/xiangxiang": 1,
		__DIR__"npc/huangyi": 1,   
	]) );

	setup();
}
