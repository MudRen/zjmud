#include <ansi.h>
inherit ROOM;
 
int do_pick(string arg) ;

void create()
{
	set("short", "ɽ��");
	set("long",@LONG
��������һ��Сɽ���С�������ߺܰ���ֻ������ԼԼ����������
һ�Ѹɲݡ���ͻȻ�ŵ�һ�����ŵ���ζ����Ȼ�����˳���ס������ȴ��
��ɨ��Ե�ʣ���������û��һ���������
LONG);   
	set("item_desc", ([
	"xia" : @TEXT
����ϸ����һ��ʯϻ�����������ƺ�����һ���飬�ƺ����������ó���(pick book)��
TEXT ]) );
	set("exits", ([
	    "out"  : __DIR__"road5",
	]));
	setup();
}
