// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "��ʶ�");
	set("long", @LONG
�˴�����̩ɽ������������һ����۹ۣ���ǰΪ�ŵǷ�̨����
���ʵ۷�������ʽ������������С�̨����һ���ֱ�����˵�Ǻ���
����������Զ����һʯ�٣����顸����С���´������������ϱ���
������������֮��������̨��
LONG );
	set("exits", ([
		"southdown" : __DIR__"nantian",
		"eastdown"  : __DIR__"riguan",
		"west"      : __DIR__"zhangren",
		"up"	: __DIR__"fengchan",
	]));
	set("objects",([
		__DIR__"npc/wei-shi2" : 3,
	]));
	set("outdoors", "taishan");
	setup();
}
