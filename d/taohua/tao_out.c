#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
	set("short", "���ֱ�");
	set("long",@LONG
����һƬ�һ��ĺ�������һ���޼ʣ�ȫ��ʢ�����һ���΢�������
��Ӣ�ͷס���Χ�����ĵġ�Զ��ż������һ����С�������һƬ��
���֣���������һ��Сͤ�ӡ�
LONG );
       	set("exits", ([
	   	"south" : __DIR__"tingzi",
	   	"north" : __DIR__"tao0",
       	]));
       	set("outdoors","taohua");
       	setup();
}

