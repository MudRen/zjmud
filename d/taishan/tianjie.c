// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "���");
	set("long", @LONG
�˵��������Ŷ�������������ʮ��С���۶����С�����������
���߱��������壬������Χ��ɽ�����ϱ�ص������š�
LONG );
	set("exits", ([
		"westdown" : __DIR__"nantian",
		"eastup" : __DIR__"weipin",
		"eastdown" : __DIR__"lianhua",
	]));
	set("objects",([
		__DIR__"npc/xiao-fan" : 2,
		__DIR__"npc/tiao-fu" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

