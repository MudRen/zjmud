#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "�ذ���");
	set("long", @LONG
���������Ͻ��ǵذ��ţ��ߴ�ĳ������Ϸ����š��ذ��š��������֣���
ʵ��̵Ĺų�ǽ�߸������š��������������վ�ż�����������ϸ�ļ�������
��Ϸ��ɵذ��Ŵ��ͨ�����ǵ����ġ�
LONG );
	set("exits", ([
		"south" : __DIR__"di_dajie2",
	]));
	set("objects", ([
		__DIR__"npc/ducha" : 1,
		__DIR__"npc/bing2" : 1,
		__DIR__"npc/bing3" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

