// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����ֽС������š���һ��ĵ�ɽ���������ﶼ���ۼ�������
�������̩ɽ��һ�밡�����ǰ���վ���ʮ���̣��ܶ��˶�������
ԥ������
LONG );
	set("exits", ([
		"northup" : __DIR__"wudafu",
		"southdown" : __DIR__"huima",
	]));
	set("objects",([
		__DIR__"npc/tiao-fu" : 1,
		__DIR__"npc/tiansong" : 1,
		__DIR__"npc/tianbai" : 1,
	]));
	set("outdoors", "taishan");
	setup();
}

