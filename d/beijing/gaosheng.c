#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
һ����ģ��С�Ĳ�ݣ���ǰ��������š��������������֡���ս�������
�ŵ�һ�ɲ���������Ƣ������Ϊ֮һˬ�����Ű�����һ���ſ��������˿��ˣ�
�����̸Ц����ͷ�Ӷ����販ʿҡͷ���Ե�˵���飬���̵Ļ��æ����ͣ��
��Ҫ����������ƹʺ�ҥ�ԣ������Ǹ������ڡ�
LONG );
       set("exits", ([
		"north" : __DIR__"caroad_w2",
	]));
	set("objects", ([
		__DIR__"npc/teahuoji" : 1,
		__DIR__"npc/chake" : 2,
		__DIR__"npc/old2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

