// datang3.c ��������
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����Ǵ��õĵ���������ȫ��̵������µĵط���ȫ�����ʦ��
��������������չ����������ڵ�����һ�㶼�������������������
������ʱ�������˱���ټ���λʦ��ʦ�ã��������������еĲ��ִ�
���������˵����¡�
LONG
	);
	set("exits", ([
		"east" : __DIR__"laojundian",
		"south" : __DIR__"nairongdian",
		"west" : __DIR__"datang2",
		"north" : __DIR__"guozhendian",
	]));
	set("objects", ([
		CLASS_D("quanzhen") + "/fang" : 1,
	]));
	setup();
}
