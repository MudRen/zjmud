// jiulou.c
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "¥��¥");
	set("long", @LONG
����¥��¥����Բ�������˲�֪�������ʽ�����Ǻ���һ����
���κ������Ƕ�һ���������ﳢ�������������ֺ��ļ����˸�ʽ��
�ȡ���С��������ȥ��æ���к����ˡ�ǽ�Ϲ��ż۸����ӡ�
LONG);
	set("exits", ([
	    "north"      : __DIR__"chufang",
	    "west"      : __DIR__"road10",
	    "up"	: __DIR__"loveroom",
	]));
	set("objects", ([
	    __DIR__"npc/xiaoer2" : 1,
	]));
	set("item_desc", ([
	    "�����ӡ�" : "
������(Pork)      ��һ�������ֶ�ʮ��ͭ��
��������(Fish)    ��һ�������ֶ�ʮ��ͭ��
�ٹ��Ͱ�(Baozi)   ����ʮ��ͭ��
����Ϻ��(Shrimp)  ����ʮ��ͭ��
�л�ͯ��(Chicken) ��һ�������ֶ�ʮ��ͭ��
��������(Guihua geng)��һ�������ֶ�ʮ��ͭ��
��ƿ(Jiuping)     ��ʮ��������\n",
	]));
//	set("no_clean_up", 0);
	setup();
}

