// story:niulang ţ��֯Ů ->��Ϊ͵��ת

#include <ansi.h>

static string char_id;
static string char_name;
static string family_name;

int give_gift();
object select_character();

string prompt() { return HIY "�����´��š�" NOR; }

static mixed *story = ({
	"̫���Ͼ�����������",
	"�����������ڴ��",
	"ZZZ~~~~~",
	"$N���䵹��������ʲô��",
	"���⴫������������硢���£���������������",
	"$N�ŵ�ƨ���������ⲻ��̫���Ͼ���������",
	"̫���Ͼ���$N�����������ɶ��Ī����ѧ�Ǻ�ͷ�������ɵ���",
	"˵�����и���һ�ӣ�$N��ɽ���ȥ��",
	"$N��ǰһ�ڣ������е���һ�",
		(: give_gift :),
	"̫���Ͼ���У���ѽ�����ã��ҵ��ɵ���",		
});
object select_character()
{
	object *obs;
	object ob;
	
	obs = filter_array(all_interactive(), (: ! wizardp($1) &&
						 environment($1) &&
						 environment($1)->query("outdoors") &&
						 ! $1->query("doing") :));
	if (! sizeof(obs))
		return 0;
	
	ob = obs[random(sizeof(obs))];
	char_id = ob->query("id");
	char_name = ob->name(1);
	family_name = ob->query("family/family_name");
	return ob;
}
void create()
{
	seteuid(getuid());
		if (! objectp(select_character()))
	{
			destruct(this_object());
			return;
	}
}

mixed query_story_message(int step)
{
	mixed msg;
	
	if (step >= sizeof(story))
		return 0;
	
	msg = story[step];
	if (stringp(msg))
	{
		msg = replace_string(msg, "$N", char_name);
	}
    return msg;
}

int give_gift()
{
	STORY_D->give_gift("/clone/vip/dan_jiuzhuan", 1,
		HIM "\n��ž����һ��һ������������ɵ���������ǰ��"NOR"\n");
	return 1;
}

