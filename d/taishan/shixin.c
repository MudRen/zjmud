// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "����ʯ");
	set("long", @LONG
�������������ķ嶥���������ʯ������һ�𣬾�˵������
�Ĵ���⣬��������ʯʱʯ��㲻�ᶯҡ����֮��ҡ����ֹ��
LONG );
	set("exits", ([
		"southdown" : __DIR__"lianhua",
	]));
	set("objects", ([
		__DIR__"npc/yujizi" : 1,
		__DIR__"npc/yuyinzi" : 1,
		__DIR__"npc/yuqingzi" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

