#include <ansi.h>

inherit BUILD_ROOM;

void rtaohua(object ob);

void create()
{
    set("short", "��̲");
    set("long", @LONG
�����һ���ǰ�ĺ�̲��������һ���޼ʵĴ󺣣���������һƬ�һ��֡�
�����ĺ��������죬���ɫ��ɳ̲���ۺ���һ�����һ�ж�����ô��������
����һ�Ҵ�(chuan)��
LONG );
    set("item_desc", ([
	"chuan" : "�����һ���������ϵ�Ĵ󴬡����ϵĿ��˻����ֻҪ\n"
		  "�ϴ�(enter)�Ϳ��Ի���ԭ��\n",
    ]));
    set("exits",([
	"south" :__DIR__"tao_in",
    ]));
    set("outdoors", "taohua");
    set("max_room", 7);
    setup();
}

void init()
{
    add_action("do_enter", "enter");
}

int do_enter ( string arg )
{
    object ob;
    string dir;

    ob = this_player();
    if (arg != "chuan")
    {
	tell_object(this_player() , "��Ҫ enter �Ķ���\n" );
	return 1;
    }

    message_vision("����һ�������ϴ���æ����һ��������ඣ�\n", ob);
    message_vision("�������𷫣��������������С�\n", ob);
    ob->move(__DIR__"dahai");
    tell_object(ob, BLU "���ں��Ϻ����˺ܾúܾ�......."NOR"\n");
    call_out("rtaohua", 10, ob);
    return 1 ;
}

void rtaohua(object ob)
{
    if (! objectp(ob) || find_object(__DIR__"dahai") != environment(ob))
	return;

    tell_object(ob, "�����ڵִ�����ԭ��һ���������С������´�����\n");
    ob->move("/d/quanzhou/jiaxinggang");
}
