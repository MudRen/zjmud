// Room: /d/mingjiao/shanjiao.c
#include <room.h>
inherit ROOM;

void create()
{
    set("short", "����ɽ��");
    set("long", @LONG
������ǧ�����صĶ�´��Զ������ƺƣ��������ơ�������
Ұǧ����������������ɽΡΡ���������߳�����ְ˰���
�����̾���������Ⱥɽ֮�С�����----�Ƕ������ֺ�����������
�ط����������������������ĺ��ֵܣ�����������а������
��������Ⱥɽ֮�󣬵ȴ�����ȥ��д��һ�����ִ��档
LONG );
    set("exits", ([
	"west" : __DIR__"tomen2",
	"east" : __DIR__"gebitan5",
	"north": __DIR__"donglu",
	"south": __DIR__"jingji/enter",
    ]));

    set("objects", ([
	__DIR__"npc/seller" : 1
    ]));

    set("outdoors", "mingjiao");
    setup();
  }
