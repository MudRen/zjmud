inherit ROOM;
#include <ansi.h>

void create()
{
	set("short","��Ժ");
	set("long", @LONG
�����Ǻ��ι�����������һ��С��԰�����ҵ����Ÿ��ֻ��ݣ���������
�����Ӳ��Ѿ����úܸ��ˡ�һЩ�ʻ������ڲݴ��У������㲻�ϵ�Ʈ����
LONG );
	set("exits", ([
		"north" : __DIR__"hai_dating",
	]));

	setup();
}
