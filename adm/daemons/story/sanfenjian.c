// story:sanfenjian ���ֽ���

#include <ansi.h>

static string char_id;
static string char_name;
static string family_name;

int give_gift();
object select_character();

static mixed *story = ({
	"ֻ����������һ��������������˫��һ�С�ָ�컮�ء��������˻���ͩ�ĳ�����",
	"�������˳�һ�����е��������������л�˵����",
	"�ڻ��˱���ǰȥ������ҫ�ۣ��ۼ���Ҫ�����ҵ���ʬ��",
	"����������һ���������ϵĺ첼�����������У�˫�ָ߾٣��е�������������",
	"�ڻ��˾㶼�󾪣����˼�����",
	"�����°��������������Χ���������ѣ�����ֻ��ƾһ����ҵ��ͼ���ҡ�",
	"�����¼�Цһ����˵�������������Ҫ�ж�ȡʤ�����Ƚ�����������ˡ���",
	"����ͩ�������ã����Һ��㵥�������������ֵĸ��С���",
	"����ͩ˵�ս���ƫ�棬б����硣�����µ�˫�������������������ܡ�����ת˲�����߰��С�",
	"ֻ��һ�����У������������н������ַ��ϰ�գ����˲�Լ��ͬ�������Ȳʡ�",
	"����������ɳ����࣬˵�������������ˣ�������㣡������ȥ�ⱳ�Ϻ첼������",
	"����ͩ�������������ϼ������������ʣ�˫��ȥ���ⲿ�������˷�Ϊʥ��ġ�����������",
	"��������ɫһ�����ȵ�������ȥ��������һ�ͻȻ���ѷ�׶�������ؼ��ɶ�����",
	"��һ�±�����䣬����ͩ���Ա��ã�����һ���������š���ȫ���ֱ����䵹�����˿�ȥ��",
	"������һ�����������ݣ����ѷ�׶�����֣�������������������������",
	"����ͩ˫�����죬����������Ȼ�����������˾��Ծ�ŭ������������",
	"����ͩ��ͦ������ֻ���ö���������������������׶������������£����ڽűߡ�",
	"����ͩ����������������ȣ����ѷ�׶�Ѿ��������Լ�Ҫ����",
	"�����º������ϣ������転�������ֶ�׼����ͩ��ͷ���¡�",
	"ֻ�������µ������ֽ���ѹ�����ͩͷ�ϣ�����������������ñ�ϴ���",
	"������Ҫ��ǰԮ�֣���Ȼ�����һ��������ͩ���ֶ̽��˵�һ���������������ظ�֮�䡣",
	"�����´��һ�������㵹���������Ǻ���ۺ�һ���ʡ�",
	"����ͩ�γ��̽��������������Ѷ��������˿���������$N����΢΢һЦ��",
	"����ͩ���룺�ղŴ��������������������������ԭ��������",
	"����ͩ�������ж������СŮ�������м���֣����ʶ������մ�������",
	"$N����һЦ��˵����������$F��$N��ŮӢ�������ˡ���",
	"$N�ֵ�����������ɽ˫ӥ��λǰ�����ֽ����ھ���ʱ�����յü������񼼣������������顣��",
	"����ͩ���������������ȣ�����Ϊ�����������ֽ��������������⣬Ҳ�ɲ���һ������",
	"����ͩ�ֵ�������������Ե�����տ�����ɽ���ң������׽����ľ��д������㡣��",
	(: give_gift :),
});

void create()
{
	seteuid(getuid());

	if (! objectp(select_character()))
	{
		STORY_D->remove_story("sanfenjian");
		destruct(this_object());
		return;
	}
}

string prompt() { return HIR "�����ִ��š�" NOR; }

object select_character()
{
	object *obs;
	object ob;

	obs = filter_array(all_interactive(),
			   (: ultrap($1) &&
			      living($1) &&
			      $1->query("combat_exp") >= 2500000 &&
			      $1->query_skill("sword", 1) > 100 &&
			      $1->query_skill("sanfen-jianshu", 1) < 1 &&
			      $1->query("family/family_name") &&
			      ! wizardp($1) &&
			      ! $1->query("story/sanfenjian") :));
	if (! sizeof(obs))
		return 0;

	ob = obs[random(sizeof(obs))];
	char_id = ob->query("id");
	char_name = ob->name(1);
	family_name = ob->query("family/family_name");
	return ob;
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
		msg = replace_string(msg, "$F", family_name);
		msg = replace_string(msg, "$ID", char_id);
	}
	return msg;
}

int give_gift()
{
	object ob;

	ob = find_player(char_id);
	if (! ob) return 1;

	if (ob->query_skill("sanfen-jianshu", 1) < 50)
		ob->set_skill("sanfen-jianshu", 50);

	ob->set("story/sanfenjian", 1);
	tell_object(ob, HIC "��ӻ���ͩ����ѧϰ�������ֽ�����"NOR"\n");
	CHANNEL_D->do_channel(this_object(), "rumor", "��˵" + ob->name(1) +
			      "�ӻ���ͩ����ѧϰ�������ֽ�����");
	STORY_D->remove_story("sanfenjian");
	return 1;
}


