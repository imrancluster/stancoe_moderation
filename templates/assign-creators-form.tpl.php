<div class="assign-creators">
    <form action="" id="assign-form" method="post">

        <div class="form-item form-type-checkboxes form-item-roles">
            <label for="content-creators">Content Creators</label>

            <div id="content-creators" class="form-checkboxes">
                <?php foreach($data['creators'] as $creator): ?>
                    <div class="form-item form-type-checkbox">
                        <input type="checkbox" id="content-creator-<?php print $creator->uid; ?>" name="roles[]" value="<?php print $creator->uid; ?>" <?php print (in_array($creator->uid, $data['manager_creators'])) ? 'checked="checked"' : ''; ?> class="form-checkbox">
                        <label class="option" for="content-creator-<?php print $creator->uid; ?>"><?php print strtoupper($creator->name); ?> </label>
                    </div>
                <?php endforeach; ?>
            </div>

            <div class="form-actions form-wrapper" id="actions">
                <input type="submit" id="asign" name="asign" value="Asign" class="form-submit">
            </div>
        </div>

    </form>
</div>