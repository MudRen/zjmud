//room: /d/mingjiao/qiandian.c
inherit ROOM;

void init();

void create()
{
	set("short","����ǰ��");
	set("long", @LONG
������������۴�����ȥ����������ѩɽ����Ө��͸����
��ƺƣ��������ơ�������Ұǧ����������������ɽΡΡ��
��������������߳�����ְ˰���������ܶ��ǰ�
LONG);
       set("exits",([
	   "east"      : __DIR__"eastdian",
	   "west"      : __DIR__"westdian",
	   "north"     : __DIR__"dadian",
	   "southdown" : __DIR__"square",
       ]));
       setup();
 }

