// huizhentang.c ������
// By Lgg,1998.10

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ǵ����Աߵ�һ��������Ҳ�ǽӴ���Ҫ���˵ĵط�������
��ֻ�ڷ���һ�����Ӻͼ������ӡ����ϰڷ���һ������ɽʯ����
����ǽ���Ϲ���һЩ�ֻ���
LONG
	);
	set("exits", ([
		"east" : __DIR__"cetang",
		"north" : __DIR__"wanwutang",
		"south" : __DIR__"datang1",
	]));
	set("objects",([
	      CLASS_D("quanzhen") + "/cui" : 1,
	]));

	setup();
}
