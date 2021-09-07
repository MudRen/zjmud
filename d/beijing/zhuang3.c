#include <room.h>
#include <ansi.h>

inherit ROOM;
int do_break(string arg);

void create()
{
    set("short", "ׯ������");
    set("long", @LONG
���������ʿׯ�ʳǵľɾӡ��Դ�������͢ץ�ߺ���������
û����ס�ˡ�һ�ȴ���(men)�����ţ� ��Χ�Ǹ߸ߵ�Χǽ(wall)��һ
�ж��ܸɾ�����û�л����ٻҳ���
LONG );
    set("exits", ([
	"south" : __DIR__"zhuang2",
    ]));
    set("item_desc", ([
	"�����š�" : "�����������ŵģ����������(break)����\n"
	ZJOBACTS2"����:break men\n",
    ]) );
    setup();
}

void init()
{
    object book, me;
    me = this_player();
    add_action("do_break", "break");
}

int do_break(string arg)
{
    int n;
    n = this_player()->query("neili");
    if (! arg || arg != "men")
    {
	write("��Ҫ��������˵Ķ�����\n");
	return 1;
    }


    message_vision("$N�ߵ���ǰ������һ������˫��ͬʱ�ĳ���\n",
		   this_player());
	
    if (n >= 200)
    {
	message_vision("$Nֻ��һ�����죬$N�������ˣ�\n",
		       this_player());
	set("exits/north", __DIR__"zhuang5");
	this_player()->set("neili",n-200);
	remove_call_out("close");
	call_out("close", 5, this_object());
    } else
    {
	message_vision("$N���һ���������������ʲôҲû������"
		       "����$N����������ǿ��\n", this_player());
	this_player()->set("neili",0);
    }

    return 1;
}
