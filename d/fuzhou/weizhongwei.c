// jiulou.c
#include <room.h>
inherit ROOM;
void create()
{
	set("short", "ζ��ζ");
	set("long", @LONG
����¥��¥����Բ�������˲�֪�������ʽ���˾���
����һ�������κ������Ƕ�һ���������ﳢ��������������
���ļ����˸�ʽ�˵ȡ���С��������ȥ��æ���к����ˡ�
ǽ�Ϲ��ż۸����ӡ�
LONG);
	set("exits", ([
	    "west"  : __DIR__"nandajie",
	    "north"  : __DIR__"chufang",
	]));
	set("objects", ([
	    __DIR__"npc/xiaoer3" : 1,
	]));
	set("item_desc", ([
	    "�����ӡ�" : "
����ǽ(Fotiaoqiang)   ����������
�����Ͼ�(Jiuping)     ����������\n",
	]));
	setup();
}

