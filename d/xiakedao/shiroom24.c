// /d/xiakedao/shishi24.c ���͵� ʯ��24

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
������谵��ֻ������������ľ������ϥ���ڽ���֮�ϣ����
ʯ��(wall)�������˼����ʯ������ɽ�������ȴ�����ߴ����
���½����ˡ����л�������������Ķ�����֮�ࡣ
LONG );
	set("exits", ([
		"east" : __DIR__"shihole6",
	]));
	set("item_desc", ([
		"��ʯ�ڡ�" : "ǽ�����Ϸ����š�����̫�������������֡��ֵ��·��̵�����������"
				"������ģ���ǧ�������������������룬����������ֱ��б����"
				"�µĴ�Ƭ�������һ���ѷִ���ίʵ���Ա��ϡ�\n"
		ZJOBACTS2"��Ħ:study wall\n",
	]));
	set("objects", ([
		CLASS_D("xiakedao") + "/long" : 1,
		CLASS_D("xiakedao") + "/mu"   : 1,
	]));
	set("no_fight", 1);
	setup();
}

#include "/d/xiakedao/shiroom.h"
